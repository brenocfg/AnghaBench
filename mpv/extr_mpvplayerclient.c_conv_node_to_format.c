#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_option {TYPE_1__* type; } ;
struct TYPE_7__ {double int64; scalar_t__ double_; } ;
struct TYPE_6__ {scalar_t__ format; TYPE_3__ u; } ;
typedef  TYPE_2__ mpv_node ;
typedef  scalar_t__ mpv_format ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ MPV_FORMAT_DOUBLE ; 
 scalar_t__ MPV_FORMAT_INT64 ; 
 struct m_option* get_mp_type (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool conv_node_to_format(void *dst, mpv_format dst_fmt, mpv_node *src)
{
    if (dst_fmt == src->format) {
        const struct m_option *type = get_mp_type(dst_fmt);
        memcpy(dst, &src->u, type->type->size);
        return true;
    }
    if (dst_fmt == MPV_FORMAT_DOUBLE && src->format == MPV_FORMAT_INT64) {
        *(double *)dst = src->u.int64;
        return true;
    }
    if (dst_fmt == MPV_FORMAT_INT64 && src->format == MPV_FORMAT_DOUBLE) {
        if (src->u.double_ >= INT64_MIN && src->u.double_ <= INT64_MAX) {
            *(int64_t *)dst = src->u.double_;
            return true;
        }
    }
    return false;
}