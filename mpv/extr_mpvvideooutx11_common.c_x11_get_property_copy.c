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
struct vo_x11_state {int dummy; } ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  XFree (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* x11_get_property (struct vo_x11_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static bool x11_get_property_copy(struct vo_x11_state *x11, Window w,
                                  Atom property, Atom type, int format,
                                  void *dst, size_t dst_size)
{
    bool ret = false;
    int len;
    void *ptr = x11_get_property(x11, w, property, type, format, &len);
    if (ptr) {
        size_t ib = format == 32 ? sizeof(long) : format / 8;
        if (dst_size / ib >= len) {
            memcpy(dst, ptr, dst_size);
            ret = true;
        }
        XFree(ptr);
    }
    return ret;
}