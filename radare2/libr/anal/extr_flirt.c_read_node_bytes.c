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
typedef  int ut64 ;
struct TYPE_3__ {int length; int* pattern_bytes; int* variant_bool_array; int variant_mask; } ;
typedef  TYPE_1__ RFlirtNode ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ buf_eof ; 
 scalar_t__ buf_err ; 
 void* malloc (int) ; 
 int read_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool read_node_bytes(RFlirtNode *node, RBuffer *b) {
	/*Reads the node bytes, and also sets the variant bytes in variant_bool_array*/
	/*returns false on parsing error*/
	int i;
	ut64 current_mask_bit = 0;
	if ((int) node->length < 0) {
		return false;
	}
	current_mask_bit = 1ULL << (node->length - 1);
	if (!(node->pattern_bytes = malloc (node->length))) {
		return false;
	}
	if (!(node->variant_bool_array = malloc (node->length))) {
		return false;
	}
	for (i = 0; i < node->length; i++, current_mask_bit >>= 1) {
		node->variant_bool_array[i] =
			(node->variant_mask & current_mask_bit)? true: false;
		if (node->variant_mask & current_mask_bit) {
			node->pattern_bytes[i] = 0x00;
		} else {
			node->pattern_bytes[i] = read_byte (b);
			if (buf_eof || buf_err) {
				return false;
			}
		}
	}
	return true;
}