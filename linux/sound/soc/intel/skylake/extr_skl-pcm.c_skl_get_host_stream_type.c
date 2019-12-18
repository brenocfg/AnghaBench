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
struct hdac_bus {scalar_t__ ppcap; } ;
typedef  enum hdac_ext_stream_type { ____Placeholder_hdac_ext_stream_type } hdac_ext_stream_type ;

/* Variables and functions */
 int HDAC_EXT_STREAM_TYPE_COUPLED ; 
 int HDAC_EXT_STREAM_TYPE_HOST ; 

__attribute__((used)) static enum hdac_ext_stream_type skl_get_host_stream_type(struct hdac_bus *bus)
{
	if (bus->ppcap)
		return HDAC_EXT_STREAM_TYPE_HOST;
	else
		return HDAC_EXT_STREAM_TYPE_COUPLED;
}