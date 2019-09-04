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
typedef  int ut8 ;
typedef  int ut64 ;
struct TYPE_3__ {int length; void* variant_mask; } ;
typedef  TYPE_1__ RFlirtNode ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ buf_eof ; 
 scalar_t__ buf_err ; 
 void* read_max_2_bytes (int /*<<< orphan*/ *) ; 
 void* read_multiple_bytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut8 read_node_variant_mask(RFlirtNode *node, RBuffer *b) {
	/*Reads and sets a node's variant bytes mask. This mask is then used to*/
	/*read the non-variant bytes following.*/
	/*returns false on parsing error*/
	if (node->length < 0x10) {
		node->variant_mask = read_max_2_bytes (b);
		if (buf_eof || buf_err) {
			return false;
		}
	} else if (node->length <= 0x20) {
		node->variant_mask = read_multiple_bytes (b);
		if (buf_eof || buf_err) {
			return false;
		}
	} else if (node->length <= 0x40) { // it shouldn't be more than 64 bytes
		node->variant_mask = ((ut64)read_multiple_bytes (b) << 32) + read_multiple_bytes (b);
		if (buf_eof || buf_err) {
			return false;
		}
	}

	return true;
}