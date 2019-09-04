#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_DUAL ; 
 int /*<<< orphan*/  MODE_TARGET ; 
 int /*<<< orphan*/  MODE_UNKNOWN ; 
#define  QLA2XXX_INI_MODE_DISABLED 131 
#define  QLA2XXX_INI_MODE_DUAL 130 
#define  QLA2XXX_INI_MODE_ENABLED 129 
#define  QLA2XXX_INI_MODE_EXCLUSIVE 128 
 int ql2x_ini_mode ; 

__attribute__((used)) static void qlt_set_mode(struct scsi_qla_host *vha)
{
	switch (ql2x_ini_mode) {
	case QLA2XXX_INI_MODE_DISABLED:
	case QLA2XXX_INI_MODE_EXCLUSIVE:
		vha->host->active_mode = MODE_TARGET;
		break;
	case QLA2XXX_INI_MODE_ENABLED:
		vha->host->active_mode = MODE_UNKNOWN;
		break;
	case QLA2XXX_INI_MODE_DUAL:
		vha->host->active_mode = MODE_DUAL;
		break;
	default:
		break;
	}
}