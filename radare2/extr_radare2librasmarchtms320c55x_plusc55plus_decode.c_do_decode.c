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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */
 scalar_t__ C55PLUS_DEBUG ; 
 char* decode_ins (int,int,int,int*,int*,int*,int,int,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_hash_code (int) ; 
 char* get_hex_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ins_part (int,int) ; 
 scalar_t__ is_hash (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  set_magic_value (int*,int,int*) ; 
 char* strcat_dup (char*,char*,int) ; 

__attribute__((used)) static char *do_decode(ut32 ins_off, ut32 ins_pos, ut32 two_ins, ut32 *next_ins_pos,
	st32 *ins_hash_code, int *err_code)
{
	st32 hash_code, hash_aux;
	ut32 reg_len_dec, ins_len_dec, ret_ins_bits;
	char *ins_res = NULL, *ins_aux = NULL;
	ut32 magic_value = 0x800;

	*next_ins_pos = 0;

	reg_len_dec = 0;
	ret_ins_bits = 0;
	ins_len_dec = 0;

	hash_code = get_hash_code(ins_pos + ins_off);
	if (is_hash(hash_code)) {
		hash_aux = hash_code;
		ins_off++;
		set_magic_value(&magic_value, hash_code, err_code);
		if (*err_code < 0) {
			return NULL;
		}
		hash_code = get_hash_code(ins_pos + ins_off);
		*next_ins_pos = 1;
	} else {
		hash_aux = 0x223;
	}

	if (ins_hash_code != NULL) {
		*ins_hash_code = hash_code;
	}

	if (C55PLUS_DEBUG) {
		printf("MAGIC VALUE 0x%x\n", 0x800);
	}

	if (hash_aux == 0x1E1 || hash_aux == 0x1E2) {
		ins_aux = decode_ins(hash_aux, ins_pos, ins_off, &ins_len_dec, &reg_len_dec,
			&ret_ins_bits, magic_value, two_ins, err_code);
		if(*err_code < 0) {
			return NULL;
		}
		ins_aux = strcat_dup(ins_aux, " ", 1);
	}

	if (hash_code == 0x223) {
		ins_res = strcat_dup(ins_aux, ".byte 0x", 1);
		ins_aux = get_hex_str(get_ins_part(ins_pos, 1));
		ins_res = strcat_dup(ins_res, ins_aux, 2);
		*next_ins_pos = *next_ins_pos + 1;
	} else {
		free (ins_aux);
		ins_aux = decode_ins(hash_code, ins_pos, ins_off, &ins_len_dec,
			&reg_len_dec, &ret_ins_bits, magic_value, two_ins, err_code);
		if (*err_code < 0) {
			free (ins_aux);
			return NULL;
		}
		ins_res = strcat_dup(ins_aux, ins_res, 1);
		//printf("NEXT POS %d %d\n", ins_len_dec, reg_len_dec);
		//getchar();
		*next_ins_pos += ins_len_dec; // reg_len_dec;
	}

	return ins_res;
}