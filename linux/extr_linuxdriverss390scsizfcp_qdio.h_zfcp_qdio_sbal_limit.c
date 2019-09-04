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
struct zfcp_qdio_req {int sbal_limit; int sbal_first; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_free; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline
void zfcp_qdio_sbal_limit(struct zfcp_qdio *qdio,
			  struct zfcp_qdio_req *q_req, int max_sbals)
{
	int count = min(atomic_read(&qdio->req_q_free), max_sbals);

	q_req->sbal_limit = (q_req->sbal_first + count - 1) %
				QDIO_MAX_BUFFERS_PER_Q;
}