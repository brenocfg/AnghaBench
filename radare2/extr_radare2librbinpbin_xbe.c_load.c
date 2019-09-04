#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ep; } ;
typedef  TYPE_2__ xbe_header ;
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_9__ {int ep_key; int /*<<< orphan*/  kt_key; TYPE_2__* header; } ;
typedef  TYPE_3__ r_bin_xbe_obj_t ;
typedef  int /*<<< orphan*/  r_bin_plugin_xbe ;
struct TYPE_10__ {TYPE_1__* o; int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {TYPE_3__* bin_obj; } ;
typedef  TYPE_4__ RBinFile ;

/* Variables and functions */
 int XBE_EP_CHIHIRO ; 
 int XBE_EP_DEBUG ; 
 int XBE_EP_RETAIL ; 
 int /*<<< orphan*/  XBE_KP_CHIHIRO ; 
 int /*<<< orphan*/  XBE_KP_DEBUG ; 
 int /*<<< orphan*/  XBE_KP_RETAIL ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/ * r_buf_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load(RBinFile *bf) {
	if (!bf || !bf->o) {
		return false;
	}
	r_bin_xbe_obj_t *obj = NULL;
	const ut8 *bytes = r_buf_buffer (bf->buf, NULL);
	bf->o->bin_obj = malloc (sizeof (r_bin_plugin_xbe));
	obj = bf->o->bin_obj;
	if (obj) {
		obj->header = (xbe_header *) bytes;
		if ((obj->header->ep & 0xf0000000) == 0x40000000) {
			// Sega Chihiro xbe
			obj->ep_key = XBE_EP_CHIHIRO;
			obj->kt_key = XBE_KP_CHIHIRO;
		} else if ((obj->header->ep ^ XBE_EP_RETAIL) > 0x1000000) {
			// Debug xbe
			obj->ep_key = XBE_EP_DEBUG;
			obj->kt_key = XBE_KP_DEBUG;
		} else {
			// Retail xbe
			obj->ep_key = XBE_EP_RETAIL;
			obj->kt_key = XBE_KP_RETAIL;
		}
		return true;
	}
	return false;
}