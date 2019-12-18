#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int stbi_uc ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int* stbi__convert_format (int*,int,int,int,int) ; 
 int* stbi__errpuc (char*,char*) ; 
 int stbi__get16be (int /*<<< orphan*/ *) ; 
 int stbi__get32be (int /*<<< orphan*/ *) ; 
 void* stbi__get8 (int /*<<< orphan*/ *) ; 
 scalar_t__ stbi__malloc (int) ; 
 int /*<<< orphan*/  stbi__skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static stbi_uc *stbi__psd_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   int   pixelCount;
   int channelCount, compression;
   int channel, i, count, len;
   int bitdepth;
   int w,h;
   stbi_uc *out;

   // Check identifier
   if (stbi__get32be(s) != 0x38425053)   // "8BPS"
      return stbi__errpuc("not PSD", "Corrupt PSD image");

   // Check file type version.
   if (stbi__get16be(s) != 1)
      return stbi__errpuc("wrong version", "Unsupported version of PSD image");

   // Skip 6 reserved bytes.
   stbi__skip(s, 6 );

   // Read the number of channels (R, G, B, A, etc).
   channelCount = stbi__get16be(s);
   if (channelCount < 0 || channelCount > 16)
      return stbi__errpuc("wrong channel count", "Unsupported number of channels in PSD image");

   // Read the rows and columns of the image.
   h = stbi__get32be(s);
   w = stbi__get32be(s);

   // Make sure the depth is 8 bits.
   bitdepth = stbi__get16be(s);
   if (bitdepth != 8 && bitdepth != 16)
      return stbi__errpuc("unsupported bit depth", "PSD bit depth is not 8 or 16 bit");

   // Make sure the color mode is RGB.
   // Valid options are:
   //   0: Bitmap
   //   1: Grayscale
   //   2: Indexed color
   //   3: RGB color
   //   4: CMYK color
   //   7: Multichannel
   //   8: Duotone
   //   9: Lab color
   if (stbi__get16be(s) != 3)
      return stbi__errpuc("wrong color format", "PSD is not in RGB color format");

   // Skip the Mode Data.  (It's the palette for indexed color; other info for other modes.)
   stbi__skip(s,stbi__get32be(s) );

   // Skip the image resources.  (resolution, pen tool paths, etc)
   stbi__skip(s, stbi__get32be(s) );

   // Skip the reserved data.
   stbi__skip(s, stbi__get32be(s) );

   // Find out if the data is compressed.
   // Known values:
   //   0: no compression
   //   1: RLE compressed
   compression = stbi__get16be(s);
   if (compression > 1)
      return stbi__errpuc("bad compression", "PSD has an unknown compression format");

   // Create the destination image.
   out = (stbi_uc *) stbi__malloc(4 * w*h);
   if (!out) return stbi__errpuc("outofmem", "Out of memory");
   pixelCount = w*h;

   // Initialize the data to zero.
   //memset( out, 0, pixelCount * 4 );

   // Finally, the image data.
   if (compression) {
      // RLE as used by .PSD and .TIFF
      // Loop until you get the number of unpacked bytes you are expecting:
      //     Read the next source byte into n.
      //     If n is between 0 and 127 inclusive, copy the next n+1 bytes literally.
      //     Else if n is between -127 and -1 inclusive, copy the next byte -n+1 times.
      //     Else if n is 128, noop.
      // Endloop

      // The RLE-compressed data is preceeded by a 2-byte data count for each row in the data,
      // which we're going to just skip.
      stbi__skip(s, h * channelCount * 2 );

      // Read the RLE data by channel.
      for (channel = 0; channel < 4; channel++) {
         stbi_uc *p;

         p = out+channel;
         if (channel >= channelCount) {
            // Fill this channel with default data.
            for (i = 0; i < pixelCount; i++, p += 4)
               *p = (channel == 3 ? 255 : 0);
         } else {
            // Read the RLE data.
            count = 0;
            while (count < pixelCount) {
               len = stbi__get8(s);
               if (len == 128) {
                  // No-op.
               } else if (len < 128) {
                  // Copy next len+1 bytes literally.
                  len++;
                  count += len;
                  while (len) {
                     *p = stbi__get8(s);
                     p += 4;
                     len--;
                  }
               } else if (len > 128) {
                  stbi_uc   val;
                  // Next -len+1 bytes in the dest are replicated from next source byte.
                  // (Interpret len as a negative 8-bit int.)
                  len ^= 0x0FF;
                  len += 2;
                  val = stbi__get8(s);
                  count += len;
                  while (len) {
                     *p = val;
                     p += 4;
                     len--;
                  }
               }
            }
         }
      }

   } else {
      // We're at the raw image data.  It's each channel in order (Red, Green, Blue, Alpha, ...)
      // where each channel consists of an 8-bit value for each pixel in the image.

      // Read the data by channel.
      for (channel = 0; channel < 4; channel++) {
         stbi_uc *p;

         p = out + channel;
         if (channel >= channelCount) {
            // Fill this channel with default data.
            stbi_uc val = channel == 3 ? 255 : 0;
            for (i = 0; i < pixelCount; i++, p += 4)
               *p = val;
         } else {
            // Read the data.
            if (bitdepth == 16) {
               for (i = 0; i < pixelCount; i++, p += 4)
                  *p = (stbi_uc) (stbi__get16be(s) >> 8);
            } else {
               for (i = 0; i < pixelCount; i++, p += 4)
                  *p = stbi__get8(s);
            }
         }
      }
   }

   if (req_comp && req_comp != 4) {
      out = stbi__convert_format(out, 4, req_comp, w, h);
      if (out == NULL) return out; // stbi__convert_format frees input on failure
   }

   if (comp) *comp = 4;
   *y = h;
   *x = w;

   return out;
}