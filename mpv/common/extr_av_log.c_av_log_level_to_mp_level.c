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

/* Variables and functions */
 int AV_LOG_ERROR ; 
 int AV_LOG_FATAL ; 
 int AV_LOG_INFO ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
 int MSGL_DEBUG ; 
 int MSGL_ERR ; 
 int MSGL_FATAL ; 
 int MSGL_TRACE ; 
 int MSGL_V ; 
 int MSGL_WARN ; 

__attribute__((used)) static int av_log_level_to_mp_level(int av_level)
{
    if (av_level > AV_LOG_VERBOSE)
        return MSGL_TRACE;
    if (av_level > AV_LOG_INFO)
        return MSGL_DEBUG;
    if (av_level > AV_LOG_WARNING)
        return MSGL_V;
    if (av_level > AV_LOG_ERROR)
        return MSGL_WARN;
    if (av_level > AV_LOG_FATAL)
        return MSGL_ERR;
    return MSGL_FATAL;
}