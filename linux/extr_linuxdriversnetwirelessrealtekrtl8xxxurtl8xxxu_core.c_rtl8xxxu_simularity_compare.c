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
typedef  size_t u32 ;
struct rtl8xxxu_priv {int tx_paths; } ;

/* Variables and functions */
 size_t MAX_TOLERANCE ; 

__attribute__((used)) static bool rtl8xxxu_simularity_compare(struct rtl8xxxu_priv *priv,
					int result[][8], int c1, int c2)
{
	u32 i, j, diff, simubitmap, bound = 0;
	int candidate[2] = {-1, -1};	/* for path A and path B */
	bool retval = true;

	if (priv->tx_paths > 1)
		bound = 8;
	else
		bound = 4;

	simubitmap = 0;

	for (i = 0; i < bound; i++) {
		diff = (result[c1][i] > result[c2][i]) ?
			(result[c1][i] - result[c2][i]) :
			(result[c2][i] - result[c1][i]);
		if (diff > MAX_TOLERANCE) {
			if ((i == 2 || i == 6) && !simubitmap) {
				if (result[c1][i] + result[c1][i + 1] == 0)
					candidate[(i / 4)] = c2;
				else if (result[c2][i] + result[c2][i + 1] == 0)
					candidate[(i / 4)] = c1;
				else
					simubitmap = simubitmap | (1 << i);
			} else {
				simubitmap = simubitmap | (1 << i);
			}
		}
	}

	if (simubitmap == 0) {
		for (i = 0; i < (bound / 4); i++) {
			if (candidate[i] >= 0) {
				for (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] = result[candidate[i]][j];
				retval = false;
			}
		}
		return retval;
	} else if (!(simubitmap & 0x0f)) {
		/* path A OK */
		for (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
	} else if (!(simubitmap & 0xf0) && priv->tx_paths > 1) {
		/* path B OK */
		for (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
	}

	return false;
}