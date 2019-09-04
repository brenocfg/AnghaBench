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
typedef  int u16 ;
struct gb_host_device {int /*<<< orphan*/  cport_id_map; } ;
struct es2_ap_dev {int cdsi1_in_use; } ;

/* Variables and functions */
#define  ES2_CPORT_CDSI1 128 
 struct es2_ap_dev* hd_to_es2 (struct gb_host_device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void es2_cport_release(struct gb_host_device *hd, u16 cport_id)
{
	struct es2_ap_dev *es2 = hd_to_es2(hd);

	switch (cport_id) {
	case ES2_CPORT_CDSI1:
		es2->cdsi1_in_use = false;
		return;
	}

	ida_simple_remove(&hd->cport_id_map, cport_id);
}