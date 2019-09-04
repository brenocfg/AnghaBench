#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int g; } ;
struct TYPE_11__ {TYPE_1__ lldb; scalar_t__ qXfer_features_read; } ;
struct TYPE_12__ {int data_len; char* data; TYPE_2__ stub_features; } ;
typedef  TYPE_3__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbr_read_target_xml (TYPE_3__*) ; 
 scalar_t__ read_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  reg_cache_init (TYPE_3__*) ; 
 scalar_t__ send_ack (TYPE_3__*) ; 
 scalar_t__ send_msg (TYPE_3__*,char*) ; 

__attribute__((used)) static int gdbr_connect_lldb(libgdbr_t *g) {
	reg_cache_init (g);
	if (g->stub_features.qXfer_features_read) {
		gdbr_read_target_xml (g);
	}
	// Check if 'g' packet is supported
	if (send_msg (g, "g") < 0 || read_packet (g, false) < 0 || send_ack (g) < 0) {
		return -1;
	}
	if (g->data_len == 0 || (g->data_len == 3 && g->data[0] == 'E')) {
		return 0;
	}
	g->stub_features.lldb.g = true;
	return 0;
}