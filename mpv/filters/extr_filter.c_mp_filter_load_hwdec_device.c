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
struct mp_stream_info {int /*<<< orphan*/  hwdec_devs; } ;
struct mp_filter {int dummy; } ;
struct AVBufferRef {int dummy; } ;

/* Variables and functions */
 struct AVBufferRef* hwdec_devices_get_lavc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwdec_devices_request_all (int /*<<< orphan*/ ) ; 
 struct mp_stream_info* mp_filter_find_stream_info (struct mp_filter*) ; 

struct AVBufferRef *mp_filter_load_hwdec_device(struct mp_filter *f, int avtype)
{
    struct mp_stream_info *info = mp_filter_find_stream_info(f);
    if (!info || !info->hwdec_devs)
        return NULL;

    hwdec_devices_request_all(info->hwdec_devs);

    return hwdec_devices_get_lavc(info->hwdec_devs, avtype);
}