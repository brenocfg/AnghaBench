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
struct zfcp_fc_wka_port {int dummy; } ;
struct bsg_job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_fc_ct_els_job_handler (void*) ; 
 struct zfcp_fc_wka_port* zfcp_fc_job_wka_port (struct bsg_job*) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_put (struct zfcp_fc_wka_port*) ; 

__attribute__((used)) static void zfcp_fc_ct_job_handler(void *data)
{
	struct bsg_job *job = data;
	struct zfcp_fc_wka_port *wka_port;

	wka_port = zfcp_fc_job_wka_port(job);
	zfcp_fc_wka_port_put(wka_port);

	zfcp_fc_ct_els_job_handler(data);
}