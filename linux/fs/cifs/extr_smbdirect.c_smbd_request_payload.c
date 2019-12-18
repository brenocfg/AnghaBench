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
struct smbd_request {scalar_t__ packet; } ;

/* Variables and functions */

__attribute__((used)) static inline void *smbd_request_payload(struct smbd_request *request)
{
	return (void *)request->packet;
}