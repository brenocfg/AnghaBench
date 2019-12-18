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
struct http_proxy_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct http_proxy_info*) ; 

void
http_proxy_close(struct http_proxy_info *hp)
{
    free(hp);
}