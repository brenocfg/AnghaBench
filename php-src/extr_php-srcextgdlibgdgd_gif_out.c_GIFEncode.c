#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_4__ {int Interlace; int in_count; int Width; int Height; long CountDown; scalar_t__ cury; scalar_t__ curx; scalar_t__ Pass; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 int /*<<< orphan*/  compress (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gdPutBuf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdPutC (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gifPutWord (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
GIFEncode(gdIOCtxPtr fp, int GWidth, int GHeight, int GInterlace, int Background, int Transparent, int BitsPerPixel, int *Red, int *Green, int *Blue, gdImagePtr im)
{
        int B;
        int RWidth, RHeight;
        int LeftOfs, TopOfs;
        int Resolution;
        int ColorMapSize;
        int InitCodeSize;
        int i;
		GifCtx ctx;

		memset(&ctx, 0, sizeof(ctx));
        ctx.Interlace = GInterlace;
		ctx.in_count = 1;

        ColorMapSize = 1 << BitsPerPixel;

        RWidth = ctx.Width = GWidth;
        RHeight = ctx.Height = GHeight;
        LeftOfs = TopOfs = 0;

        Resolution = BitsPerPixel;

        /*
         * Calculate number of bits we are expecting
         */
        ctx.CountDown = (long)ctx.Width * (long)ctx.Height;

        /*
         * Indicate which pass we are on (if interlace)
         */
        ctx.Pass = 0;

        /*
         * The initial code size
         */
        if( BitsPerPixel <= 1 )
                InitCodeSize = 2;
        else
                InitCodeSize = BitsPerPixel;

        /*
         * Set up the current x and y position
         */
        ctx.curx = ctx.cury = 0;

        /*
         * Write the Magic header
         */
        gdPutBuf(Transparent < 0 ? "GIF87a" : "GIF89a", 6, fp );

        /*
         * Write out the screen width and height
         */
        gifPutWord( RWidth, fp );
        gifPutWord( RHeight, fp );

        /*
         * Indicate that there is a global colour map
         */
        B = 0x80;       /* Yes, there is a color map */

        /*
         * OR in the resolution
         */
        B |= (Resolution - 1) << 5;

        /*
         * OR in the Bits per Pixel
         */
        B |= (BitsPerPixel - 1);

        /*
         * Write it out
         */
        gdPutC( B, fp );

        /*
         * Write out the Background colour
         */
        gdPutC( Background, fp );

        /*
         * Byte of 0's (future expansion)
         */
        gdPutC( 0, fp );

        /*
         * Write out the Global Colour Map
         */
        for( i=0; i<ColorMapSize; ++i ) {
                gdPutC( Red[i], fp );
                gdPutC( Green[i], fp );
                gdPutC( Blue[i], fp );
        }

	/*
	 * Write out extension for transparent colour index, if necessary.
	 */
	if ( Transparent >= 0 ) {
	    gdPutC( '!', fp );
	    gdPutC( 0xf9, fp );
	    gdPutC( 4, fp );
	    gdPutC( 1, fp );
	    gdPutC( 0, fp );
	    gdPutC( 0, fp );
	    gdPutC( (unsigned char) Transparent, fp );
	    gdPutC( 0, fp );
	}

        /*
         * Write an Image separator
         */
        gdPutC( ',', fp );

        /*
         * Write the Image header
         */

        gifPutWord( LeftOfs, fp );
        gifPutWord( TopOfs, fp );
        gifPutWord( ctx.Width, fp );
        gifPutWord( ctx.Height, fp );

        /*
         * Write out whether or not the image is interlaced
         */
        if( ctx.Interlace )
                gdPutC( 0x40, fp );
        else
                gdPutC( 0x00, fp );

        /*
         * Write out the initial code size
         */
        gdPutC( InitCodeSize, fp );

        /*
         * Go and actually compress the data
         */
        compress( InitCodeSize+1, fp, im, &ctx );

        /*
         * Write out a Zero-length packet (to end the series)
         */
        gdPutC( 0, fp );

        /*
         * Write the GIF file terminator
         */
        gdPutC( ';', fp );
}