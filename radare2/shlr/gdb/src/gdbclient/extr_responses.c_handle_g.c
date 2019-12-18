#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int send_ack (TYPE_1__*) ; 
 scalar_t__ unpack_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int handle_g(libgdbr_t *g) {
	if (unpack_hex (g->data, g->data_len, g->data) < 0) {
		return -1;
	}
	g->data_len = g->data_len / 2;
	return send_ack (g);
}