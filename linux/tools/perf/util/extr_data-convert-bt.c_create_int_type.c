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
struct bt_ctf_field_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CTF_BYTE_ORDER_BIG_ENDIAN ; 
 int /*<<< orphan*/  BT_CTF_BYTE_ORDER_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  BT_CTF_INTEGER_BASE_HEXADECIMAL ; 
 struct bt_ctf_field_type* bt_ctf_field_type_integer_create (int) ; 
 scalar_t__ bt_ctf_field_type_integer_set_base (struct bt_ctf_field_type*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_ctf_field_type_integer_set_signed (struct bt_ctf_field_type*,int) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (struct bt_ctf_field_type*) ; 
 int /*<<< orphan*/  bt_ctf_field_type_set_byte_order (struct bt_ctf_field_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr2 (char*,int,char*,char*) ; 

__attribute__((used)) static struct bt_ctf_field_type *create_int_type(int size, bool sign, bool hex)
{
	struct bt_ctf_field_type *type;

	type = bt_ctf_field_type_integer_create(size);
	if (!type)
		return NULL;

	if (sign &&
	    bt_ctf_field_type_integer_set_signed(type, 1))
		goto err;

	if (hex &&
	    bt_ctf_field_type_integer_set_base(type, BT_CTF_INTEGER_BASE_HEXADECIMAL))
		goto err;

#if __BYTE_ORDER == __BIG_ENDIAN
	bt_ctf_field_type_set_byte_order(type, BT_CTF_BYTE_ORDER_BIG_ENDIAN);
#else
	bt_ctf_field_type_set_byte_order(type, BT_CTF_BYTE_ORDER_LITTLE_ENDIAN);
#endif

	pr2("Created type: INTEGER %d-bit %ssigned %s\n",
	    size, sign ? "un" : "", hex ? "hex" : "");
	return type;

err:
	bt_ctf_field_type_put(type);
	return NULL;
}