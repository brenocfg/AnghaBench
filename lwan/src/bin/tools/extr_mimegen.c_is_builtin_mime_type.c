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
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static bool is_builtin_mime_type(const char *mime)
{
    /* These are the mime types supported by Lwan without having to perform
     * a bsearch().  application/octet-stream is the fallback. */
    if (streq(mime, "application/octet-stream"))
        return true;
    if (streq(mime, "application/javascript"))
        return true;
    if (streq(mime, "image/jpeg"))
        return true;
    if (streq(mime, "image/png"))
        return true;
    if (streq(mime, "text/html"))
        return true;
    if (streq(mime, "text/css"))
        return true;
    if (streq(mime, "text/plain"))
        return true;
    return false;
}