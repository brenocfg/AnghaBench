#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {TYPE_2__* adapter; } ;
struct TYPE_4__ {TYPE_1__* dbf; } ;
struct TYPE_3__ {int /*<<< orphan*/  hba; } ;

/* Variables and functions */
 scalar_t__ debug_level_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_fsf_res (char*,int,struct zfcp_fsf_req*) ; 

__attribute__((used)) static inline
void zfcp_dbf_hba_fsf_resp(char *tag, int level, struct zfcp_fsf_req *req)
{
	if (debug_level_enabled(req->adapter->dbf->hba, level))
		zfcp_dbf_hba_fsf_res(tag, level, req);
}