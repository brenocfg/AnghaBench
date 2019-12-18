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
typedef  int ut64 ;

/* Variables and functions */
 int BB_BIT ; 
 int BT_BIT ; 
 int B_BIT ; 
 int C_MATCH_BIT ; 
 int DB_BIT ; 
 int D_BIT ; 
 int EA_BIT ; 
 int EIGHT_BIT ; 
 int FD_BIT ; 
 int H_BIT ; 
 int IA_BIT ; 
 int ID_BIT ; 
 int IE_BIT ; 
 int L_BIT ; 
 int M_BIT ; 
 int R_BIT ; 
 int SH_BIT ; 
 int SIXTEEN_BIT ; 
 int S_BIT ; 
 int TB_BIT ; 
 int TT_BIT ; 
 int TWO_BIT ; 
 int T_BIT ; 
 int WB_BIT ; 
 int WT_BIT ; 
 int W_BIT ; 
 int X_BIT ; 
 int cqcheck (char**) ; 
 int /*<<< orphan*/  r_str_case (char*,int) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static ut64 opmask(char *input, char *opcode, ut64 allowed_mask) {
	ut64 res = 0;
	
	r_str_case (input, false);
	if (strlen (opcode) > strlen (input)) {
		return 0;
	}
	if (r_str_startswith (input, opcode)) {
		input += strlen (opcode);
		res |= M_BIT;
		res |= cqcheck (&input);
		
		if ((*input == 's') && (S_BIT & allowed_mask)) {
			res |= S_BIT;
			input++;
		}
		res |= cqcheck (&input);

		if ((r_str_startswith (input, "wb")) && (WB_BIT & allowed_mask)) {
			res |= WB_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "wt")) && (WT_BIT & allowed_mask)) {
			res |= WT_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if ((r_str_startswith (input, "db")) && (DB_BIT & allowed_mask)) {
			res |= DB_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "ea")) && (EA_BIT & allowed_mask)) {
			res |= EA_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "ia")) && (IA_BIT & allowed_mask)) {
			res |= IA_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "fd")) && (FD_BIT & allowed_mask)) {
			res |= FD_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if ((*input == 'l') && (L_BIT & allowed_mask)) {
			res |= L_BIT;
			input++;
		}
		res |= cqcheck (&input);
		if ((r_str_startswith (input, "bb")) && (BB_BIT & allowed_mask)) {
			res |= BB_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "tt")) && (TT_BIT & allowed_mask)) {
			res |= TT_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "bt")) && (BT_BIT & allowed_mask)) {
			res |= BT_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "tb")) && (TB_BIT & allowed_mask)) {
			res |= TB_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if ((*input == 'w') && (W_BIT & allowed_mask)) {
			res |= W_BIT;
			input++;
		}
		if ((*input == 'b') && (B_BIT & allowed_mask)) {
			res |= B_BIT;
			input++;
		} else
	        if ((*input == 'h') && (H_BIT & allowed_mask)) {
			res |= H_BIT;
			input++;
		} else
		if ((*input == 'd') && (D_BIT & allowed_mask)) {
			res |= D_BIT;
			input++;
		}
		if ((*input == 't') && (T_BIT & allowed_mask)) {
			res |= T_BIT;
			input++;
		}
		if ((*input == 's') && (S_BIT & allowed_mask)) {
			res |= S_BIT;
			input++;
		}
		res |= cqcheck (&input);
		if ((*input == 'r') && (R_BIT & allowed_mask)) {
			res |= R_BIT;
			input++;
		}
		res |= cqcheck (&input);
		if ((*input == '2') && (TWO_BIT & allowed_mask)) {
			res |= TWO_BIT;
			input++;
		}
		if ((*input == '8') && (EIGHT_BIT & allowed_mask)) {
			res |= EIGHT_BIT;
			input++;
		}
		if ((r_str_startswith (input, "16")) && (SIXTEEN_BIT & allowed_mask)) {
			res |= SIXTEEN_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if ((*input == 'l') && (L_BIT & allowed_mask)) {
			res |= L_BIT;
			input++;
		}
		if ((*input == 'x') && (X_BIT & allowed_mask)) {
			res |= X_BIT;
			input++;
		}
		res |= cqcheck (&input);
		if ((r_str_startswith (input, "id")) && (ID_BIT & allowed_mask)) {
			res |= ID_BIT;
			input += 2;
		}
		if ((r_str_startswith (input, "ie")) && (IE_BIT & allowed_mask)) {
			res |= IE_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if ((r_str_startswith (input, "sh")) && (SH_BIT & allowed_mask)) {
			res |= SH_BIT;
			input += 2;
		}
		res |= cqcheck (&input);
		if (!(res & C_MATCH_BIT)) {
			res |= 15 << 2; // nv is the default condition
		}
		if (*input == 0) {
			return res;
		}
	}
	return 0;
}