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
typedef  int GLushort ;
typedef  int GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLchan ;

/* Variables and functions */
 size_t ACOMP ; 
 size_t BCOMP ; 
 int /*<<< orphan*/  CHAN_MAX ; 
 int EXP5TO8B (int const) ; 
 int EXP5TO8R (int const) ; 
 int EXP6TO8G (int const) ; 
 size_t GCOMP ; 
 size_t RCOMP ; 
 int /*<<< orphan*/  UBYTE_TO_CHAN (int) ; 

__attribute__((used)) static void dxt135_decode_imageblock ( const GLubyte *img_block_src,
                         GLint i, GLint j, GLuint dxt_type, GLvoid *texel ) {
   GLchan *rgba = (GLchan *) texel;
   const GLushort color0 = img_block_src[0] | (img_block_src[1] << 8);
   const GLushort color1 = img_block_src[2] | (img_block_src[3] << 8);
   const GLuint bits = img_block_src[4] | (img_block_src[5] << 8) |
      (img_block_src[6] << 16) | (img_block_src[7] << 24);
   /* What about big/little endian? */
   GLubyte bit_pos = 2 * (j * 4 + i) ;
   GLubyte code = (GLubyte) ((bits >> bit_pos) & 3);

   rgba[ACOMP] = CHAN_MAX;
   switch (code) {
   case 0:
      rgba[RCOMP] = UBYTE_TO_CHAN( EXP5TO8R(color0) );
      rgba[GCOMP] = UBYTE_TO_CHAN( EXP6TO8G(color0) );
      rgba[BCOMP] = UBYTE_TO_CHAN( EXP5TO8B(color0) );
      break;
   case 1:
      rgba[RCOMP] = UBYTE_TO_CHAN( EXP5TO8R(color1) );
      rgba[GCOMP] = UBYTE_TO_CHAN( EXP6TO8G(color1) );
      rgba[BCOMP] = UBYTE_TO_CHAN( EXP5TO8B(color1) );
      break;
   case 2:
      if ((dxt_type > 1) || (color0 > color1)) {
         rgba[RCOMP] = UBYTE_TO_CHAN( ((EXP5TO8R(color0) * 2 + EXP5TO8R(color1)) / 3) );
         rgba[GCOMP] = UBYTE_TO_CHAN( ((EXP6TO8G(color0) * 2 + EXP6TO8G(color1)) / 3) );
         rgba[BCOMP] = UBYTE_TO_CHAN( ((EXP5TO8B(color0) * 2 + EXP5TO8B(color1)) / 3) );
      }
      else {
         rgba[RCOMP] = UBYTE_TO_CHAN( ((EXP5TO8R(color0) + EXP5TO8R(color1)) / 2) );
         rgba[GCOMP] = UBYTE_TO_CHAN( ((EXP6TO8G(color0) + EXP6TO8G(color1)) / 2) );
         rgba[BCOMP] = UBYTE_TO_CHAN( ((EXP5TO8B(color0) + EXP5TO8B(color1)) / 2) );
      }
      break;
   case 3:
      if ((dxt_type > 1) || (color0 > color1)) {
         rgba[RCOMP] = UBYTE_TO_CHAN( ((EXP5TO8R(color0) + EXP5TO8R(color1) * 2) / 3) );
         rgba[GCOMP] = UBYTE_TO_CHAN( ((EXP6TO8G(color0) + EXP6TO8G(color1) * 2) / 3) );
         rgba[BCOMP] = UBYTE_TO_CHAN( ((EXP5TO8B(color0) + EXP5TO8B(color1) * 2) / 3) );
      }
      else {
         rgba[RCOMP] = 0;
         rgba[GCOMP] = 0;
         rgba[BCOMP] = 0;
         if (dxt_type == 1) rgba[ACOMP] = UBYTE_TO_CHAN(0);
      }
      break;
   default:
   /* CANNOT happen (I hope) */
      break;
   }
}