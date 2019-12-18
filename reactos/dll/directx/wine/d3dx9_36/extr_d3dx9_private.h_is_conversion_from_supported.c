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
struct pixel_format_desc {scalar_t__ type; int /*<<< orphan*/  to_rgba; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FORMAT_ARGB ; 
 scalar_t__ FORMAT_ARGBF ; 
 scalar_t__ FORMAT_ARGBF16 ; 
 int TRUE ; 

__attribute__((used)) static inline BOOL is_conversion_from_supported(const struct pixel_format_desc *format)
{
    if (format->type == FORMAT_ARGB || format->type == FORMAT_ARGBF16
            || format->type == FORMAT_ARGBF)
        return TRUE;
    return !!format->to_rgba;
}