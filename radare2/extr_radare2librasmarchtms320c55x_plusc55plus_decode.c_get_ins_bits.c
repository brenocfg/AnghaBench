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
typedef  int ut8 ;
typedef  int ut32 ;

/* Variables and functions */
 scalar_t__ C55PLUS_DEBUG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int get_ins_part (int,int) ; 
 int get_q_bits (int,char*,int,int*) ; 
 int /*<<< orphan*/  getchar () ; 
 char** ins_str ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static ut32 get_ins_bits(ut32 hash_code, ut32 ins_pos, char *ins,
	ut32 ins_len, ut32 magic_value, int *err_code)
{
	ut32 res = 0;
	ut8 op_b;
	ut32 len, x, i;
	char *op_str, *aux;

	if (ins[0] == 'q') {
		return get_q_bits (magic_value, ins, ins_len, err_code);
	}

	op_str = ins_str[1 + hash_code * 4];
	//printf("OPSTR => %s %d\n", ins, ins_len);

	x = 0;
	for (i = 0; i < ins_len; i++) {
		aux = strchr(&op_str[x], ins[i]);
		if (!aux) {
			aux = strchr(op_str, ins[i]);
			if (!aux) {
				fprintf(stderr, "Invalid token %s\n", ins); *err_code = -1; return 0;
			}
		}

		len = (unsigned int)(aux - op_str);
		//printf("INS_POS: %d POS: %d\n",  ins_pos, len / 8);
		op_b = get_ins_part(ins_pos + len / 8, 1);
		//printf("OPP: %x\n", op_b);

		x = len + 1;
		res = (res * 2) | ((op_b >> ((1023 - len) % 8)) & 1);
		if (!op_str[x]) {
			x = 0;
		}
	}

	if (C55PLUS_DEBUG) {
		printf("INS_BITS => 0x%x\n", res);
		getchar();
	}

	return res;
}