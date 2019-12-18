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
struct tls_multi {char const* client_reason; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *
tls_client_reason(struct tls_multi *multi)
{
    return multi->client_reason;
}