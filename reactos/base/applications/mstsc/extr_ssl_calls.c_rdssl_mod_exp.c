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
typedef  int DIGIT_T ;

/* Variables and functions */
 int HIBITMASK ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_malloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mpModMult (int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  mpNEXTBITMASK (int,unsigned int) ; 
 int /*<<< orphan*/  mpSetEqual (int*,int*,int) ; 
 unsigned int mpSizeof (int*,int) ; 

int
rdssl_mod_exp(char* out, int out_len, char* in, int in_len,
              char* mod, int mod_len, char* exp, int exp_len)
{
  /* Computes y = x ^ e mod m */
  /* Binary left-to-right method */
  DIGIT_T mask;
  DIGIT_T* e;
  DIGIT_T* x;
  DIGIT_T* y;
  DIGIT_T* m;
  unsigned int n;
  int max_size;
  char* l_out;
  char* l_in;
  char* l_mod;
  char* l_exp;

  if (in_len > out_len || in_len == 0 ||
      out_len == 0 || mod_len == 0 || exp_len == 0)
  {
    return 0;
  }
  max_size = out_len;
  if (in_len > max_size)
  {
    max_size = in_len;
  }
  if (mod_len > max_size)
  {
    max_size = mod_len;
  }
  if (exp_len > max_size)
  {
    max_size = exp_len;
  }
  l_out = (char*)g_malloc(max_size, 1);
  l_in = (char*)g_malloc(max_size, 1);
  l_mod = (char*)g_malloc(max_size, 1);
  l_exp = (char*)g_malloc(max_size, 1);
  memcpy(l_in, in, in_len);
  memcpy(l_mod, mod, mod_len);
  memcpy(l_exp, exp, exp_len);
  e = (DIGIT_T*)l_exp;
  x = (DIGIT_T*)l_in;
  y = (DIGIT_T*)l_out;
  m = (DIGIT_T*)l_mod;
  /* Find second-most significant bit in e */
  n = mpSizeof(e, max_size / 4);
  for (mask = HIBITMASK; mask > 0; mask >>= 1)
  {
    if (e[n - 1] & mask)
    {
      break;
    }
  }
  mpNEXTBITMASK(mask, n);
  /* Set y = x */
  mpSetEqual(y, x, max_size / 4);
  /* For bit j = k - 2 downto 0 step -1 */
  while (n)
  {
    mpModMult(y, y, y, m, max_size / 4); /* Square */
    if (e[n - 1] & mask)
    {
      mpModMult(y, y, x, m, max_size / 4); /* Multiply */
    }
    /* Move to next bit */
    mpNEXTBITMASK(mask, n);
  }
  memcpy(out, l_out, out_len);
  g_free(l_out);
  g_free(l_in);
  g_free(l_mod);
  g_free(l_exp);
  return out_len;
}