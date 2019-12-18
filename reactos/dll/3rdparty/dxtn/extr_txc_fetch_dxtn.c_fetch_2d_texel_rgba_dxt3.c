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
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLchan ;

/* Variables and functions */
 size_t ACOMP ; 
 scalar_t__ EXP4TO8 (int const) ; 
 int /*<<< orphan*/  UBYTE_TO_CHAN (int) ; 
 int /*<<< orphan*/  dxt135_decode_imageblock (int const*,int,int,int,int /*<<< orphan*/ *) ; 

void fetch_2d_texel_rgba_dxt3(GLint srcRowStride, const GLubyte *pixdata,
                         GLint i, GLint j, GLvoid *texel) {

   /* Extract the (i,j) pixel from pixdata and return it
    * in texel[RCOMP], texel[GCOMP], texel[BCOMP], texel[ACOMP].
    */

   GLchan *rgba = (GLchan *) texel;
   const GLubyte *blksrc = (pixdata + ((srcRowStride + 3) / 4 * (j / 4) + (i / 4)) * 16);
#if 0
   /* Simple 32bit version. */
/* that's pretty brain-dead for a single pixel, isn't it? */
   const GLubyte bit_pos = 4 * ((j&3) * 4 + (i&3));
   const GLuint alpha_low = blksrc[0] | (blksrc[1] << 8) | (blksrc[2] << 16) | (blksrc[3] << 24);
   const GLuint alpha_high = blksrc[4] | (blksrc[5] << 8) | (blksrc[6] << 16) | (blksrc[7] << 24);

   dxt135_decode_imageblock(blksrc + 8, (i&3), (j&3), 2, texel);
   if (bit_pos < 32)
      rgba[ACOMP] = UBYTE_TO_CHAN( (GLubyte)(EXP4TO8((alpha_low >> bit_pos) & 15)) );
   else
      rgba[ACOMP] = UBYTE_TO_CHAN( (GLubyte)(EXP4TO8((alpha_high >> (bit_pos - 32)) & 15)) );
#endif
#if 1
/* TODO test this! */
   const GLubyte anibble = (blksrc[((j&3) * 4 + (i&3)) / 2] >> (4 * (i&1))) & 0xf;
   dxt135_decode_imageblock(blksrc + 8, (i&3), (j&3), 2, texel);
   rgba[ACOMP] = UBYTE_TO_CHAN( (GLubyte)(EXP4TO8(anibble)) );
#endif

}