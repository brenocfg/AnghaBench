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
struct btf_verifier_env {int dummy; } ;
struct btf_type {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INT_BITS (int) ; 
 int /*<<< orphan*/  BTF_INT_ENCODING (int) ; 
 int /*<<< orphan*/  BTF_INT_OFFSET (int) ; 
 int /*<<< orphan*/  btf_int_encoding_str (int /*<<< orphan*/ ) ; 
 int btf_type_int (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log (struct btf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_int_log(struct btf_verifier_env *env,
			const struct btf_type *t)
{
	int int_data = btf_type_int(t);

	btf_verifier_log(env,
			 "size=%u bits_offset=%u nr_bits=%u encoding=%s",
			 t->size, BTF_INT_OFFSET(int_data),
			 BTF_INT_BITS(int_data),
			 btf_int_encoding_str(BTF_INT_ENCODING(int_data)));
}