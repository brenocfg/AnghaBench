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
struct zfcp_qdio_req {scalar_t__ sbale_curr; } ;
struct zfcp_qdio {scalar_t__ max_sbale_per_sbal; } ;

/* Variables and functions */

__attribute__((used)) static inline
void zfcp_qdio_skip_to_last_sbale(struct zfcp_qdio *qdio,
				  struct zfcp_qdio_req *q_req)
{
	q_req->sbale_curr = qdio->max_sbale_per_sbal - 1;
}