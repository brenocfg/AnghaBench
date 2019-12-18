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
typedef  double __m64 ;
typedef  int /*<<< orphan*/ * JSAMPROW ;
typedef  int /*<<< orphan*/ ** JSAMPARRAY ;
typedef  int JDIMENSION ;

/* Variables and functions */
 int BYTE_BIT ; 
 int DCTSIZE ; 
 double _mm_add_pi16 (double,double) ; 
 double _mm_and_si64 (double,double) ; 
 double _mm_cmpeq_pi16 (double,double) ; 
 double _mm_load_si64 (double*) ; 
 double _mm_packs_pu16 (double,double) ; 
 double _mm_set1_pi32 (int) ; 
 double _mm_srli_pi16 (double,int) ; 
 int /*<<< orphan*/  _mm_store_si64 (double*,double) ; 
 int /*<<< orphan*/  expand_right_edge (int /*<<< orphan*/ **,int,int,int) ; 

void jsimd_h2v2_downsample_mmi(JDIMENSION image_width, int max_v_samp_factor,
                               JDIMENSION v_samp_factor,
                               JDIMENSION width_in_blocks,
                               JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int inrow, outrow, outcol, bias;
  JDIMENSION output_cols = width_in_blocks * DCTSIZE;
  JSAMPROW inptr0, inptr1, outptr;
  __m64 mm0, mm1, mm2, mm3, mm4, mm5, mm6 = 0.0, mm7;

  expand_right_edge(input_data, max_v_samp_factor, image_width,
                    output_cols * 2);

  bias = (1 << 17) + 1;                      /* 0x00020001 (bias pattern) */
  mm7 = _mm_set1_pi32(bias);                 /* mm7={1, 2, 1, 2} */
  mm6 = _mm_cmpeq_pi16(mm6, mm6);
  mm6 = _mm_srli_pi16(mm6, BYTE_BIT);        /* mm6={0xFF 0x00 0xFF 0x00 ..} */

  for (inrow = 0, outrow = 0; outrow < v_samp_factor;
       inrow += 2, outrow++) {

    inptr0 = input_data[inrow];
    inptr1 = input_data[inrow + 1];
    outptr = output_data[outrow];

    for (outcol = output_cols; outcol > 0;
         outcol -= 8, inptr0 += 16, inptr1 += 16, outptr += 8) {

      mm0 = _mm_load_si64((__m64 *)&inptr0[0]);
      mm1 = _mm_load_si64((__m64 *)&inptr1[0]);
      mm2 = _mm_load_si64((__m64 *)&inptr0[8]);
      mm3 = _mm_load_si64((__m64 *)&inptr1[8]);

      mm4 = mm0;
      mm5 = mm1;
      mm0 = _mm_and_si64(mm0, mm6);
      mm4 = _mm_srli_pi16(mm4, BYTE_BIT);
      mm1 = _mm_and_si64(mm1, mm6);
      mm5 = _mm_srli_pi16(mm5, BYTE_BIT);
      mm0 = _mm_add_pi16(mm0, mm4);
      mm1 = _mm_add_pi16(mm1, mm5);

      mm4 = mm2;
      mm5 = mm3;
      mm2 = _mm_and_si64(mm2, mm6);
      mm4 = _mm_srli_pi16(mm4, BYTE_BIT);
      mm3 = _mm_and_si64(mm3, mm6);
      mm5 = _mm_srli_pi16(mm5, BYTE_BIT);
      mm2 = _mm_add_pi16(mm2, mm4);
      mm3 = _mm_add_pi16(mm3, mm5);

      mm0 = _mm_add_pi16(mm0, mm1);
      mm2 = _mm_add_pi16(mm2, mm3);
      mm0 = _mm_add_pi16(mm0, mm7);
      mm2 = _mm_add_pi16(mm2, mm7);
      mm0 = _mm_srli_pi16(mm0, 2);
      mm2 = _mm_srli_pi16(mm2, 2);

      mm0 = _mm_packs_pu16(mm0, mm2);

      _mm_store_si64((__m64 *)&outptr[0], mm0);
    }
  }
}