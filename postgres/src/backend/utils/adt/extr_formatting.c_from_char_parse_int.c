#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ FormatNode ;

/* Variables and functions */
 int from_char_parse_int_len (int*,char**,int /*<<< orphan*/ ,TYPE_2__*,int*) ; 

__attribute__((used)) static int
from_char_parse_int(int *dest, char **src, FormatNode *node, bool *have_error)
{
	return from_char_parse_int_len(dest, src, node->key->len, node, have_error);
}