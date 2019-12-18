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
struct m_option {int dummy; } ;
typedef  scalar_t__ mpv_format ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_OSD_STRING ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 struct m_option const* get_mp_type (scalar_t__) ; 

__attribute__((used)) static const struct m_option *get_mp_type_get(mpv_format format)
{
    if (format == MPV_FORMAT_OSD_STRING)
        format = MPV_FORMAT_STRING; // it's string data, just other semantics
    return get_mp_type(format);
}