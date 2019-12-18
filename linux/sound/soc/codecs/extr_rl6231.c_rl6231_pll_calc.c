#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rl6231_pll_code {int m_bp; int m_code; int n_code; int k_code; } ;
struct TYPE_3__ {unsigned int const pll_in; unsigned int const pll_out; int k; int m; int n; int m_bp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 unsigned int const RL6231_PLL_INP_MAX ; 
 unsigned int const RL6231_PLL_INP_MIN ; 
 int RL6231_PLL_K_MAX ; 
 int RL6231_PLL_M_MAX ; 
 int RL6231_PLL_N_MAX ; 
 unsigned int abs (unsigned int const) ; 
 unsigned int find_best_div (unsigned int const,unsigned int,unsigned int) ; 
 unsigned int gcd (unsigned int const,unsigned int const) ; 
 TYPE_1__* pll_preset_table ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int rl6231_pll_calc(const unsigned int freq_in,
	const unsigned int freq_out, struct rl6231_pll_code *pll_code)
{
	int max_n = RL6231_PLL_N_MAX, max_m = RL6231_PLL_M_MAX;
	int i, k, n_t;
	int k_t, min_k, max_k, n = 0, m = 0, m_t = 0;
	unsigned int red, pll_out, in_t, out_t, div, div_t;
	unsigned int red_t = abs(freq_out - freq_in);
	unsigned int f_in, f_out, f_max;
	bool bypass = false;

	if (RL6231_PLL_INP_MAX < freq_in || RL6231_PLL_INP_MIN > freq_in)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(pll_preset_table); i++) {
		if (freq_in == pll_preset_table[i].pll_in &&
			freq_out == pll_preset_table[i].pll_out) {
			k = pll_preset_table[i].k;
			m = pll_preset_table[i].m;
			n = pll_preset_table[i].n;
			bypass = pll_preset_table[i].m_bp;
			pr_debug("Use preset PLL parameter table\n");
			goto code_find;
		}
	}

	min_k = 80000000 / freq_out - 2;
	max_k = 150000000 / freq_out - 2;
	if (max_k > RL6231_PLL_K_MAX)
		max_k = RL6231_PLL_K_MAX;
	if (min_k > RL6231_PLL_K_MAX)
		min_k = max_k = RL6231_PLL_K_MAX;
	div_t = gcd(freq_in, freq_out);
	f_max = 0xffffffff / RL6231_PLL_N_MAX;
	div = find_best_div(freq_in, f_max, div_t);
	f_in = freq_in / div;
	f_out = freq_out / div;
	k = min_k;
	for (k_t = min_k; k_t <= max_k; k_t++) {
		for (n_t = 0; n_t <= max_n; n_t++) {
			in_t = f_in * (n_t + 2);
			pll_out = f_out * (k_t + 2);
			if (in_t == pll_out) {
				bypass = true;
				n = n_t;
				k = k_t;
				goto code_find;
			}
			out_t = in_t / (k_t + 2);
			red = abs(f_out - out_t);
			if (red < red_t) {
				bypass = true;
				n = n_t;
				m = 0;
				k = k_t;
				if (red == 0)
					goto code_find;
				red_t = red;
			}
			for (m_t = 0; m_t <= max_m; m_t++) {
				out_t = in_t / ((m_t + 2) * (k_t + 2));
				red = abs(f_out - out_t);
				if (red < red_t) {
					bypass = false;
					n = n_t;
					m = m_t;
					k = k_t;
					if (red == 0)
						goto code_find;
					red_t = red;
				}
			}
		}
	}
	pr_debug("Only get approximation about PLL\n");

code_find:

	pll_code->m_bp = bypass;
	pll_code->m_code = m;
	pll_code->n_code = n;
	pll_code->k_code = k;
	return 0;
}