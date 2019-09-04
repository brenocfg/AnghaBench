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
struct scsi_device {struct clariion_dh_data* handler_data; } ;
struct clariion_dh_data {scalar_t__ lun_state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_HONOR_RESERVATIONS ; 
 scalar_t__ CLARIION_LUN_OWNED ; 
 scalar_t__ CLARIION_LUN_UNINITIALIZED ; 
 int /*<<< orphan*/  CLARIION_SHORT_TRESPASS ; 
 int EINVAL ; 
 int SCSI_DH_OK ; 
 int clariion_send_inquiry (struct scsi_device*,struct clariion_dh_data*) ; 
 int send_trespass_cmd (struct scsi_device*,struct clariion_dh_data*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static int clariion_set_params(struct scsi_device *sdev, const char *params)
{
	struct clariion_dh_data *csdev = sdev->handler_data;
	unsigned int hr = 0, st = 0, argc;
	const char *p = params;
	int result = SCSI_DH_OK;

	if ((sscanf(params, "%u", &argc) != 1) || (argc != 2))
		return -EINVAL;

	while (*p++)
		;
	if ((sscanf(p, "%u", &st) != 1) || (st > 1))
		return -EINVAL;

	while (*p++)
		;
	if ((sscanf(p, "%u", &hr) != 1) || (hr > 1))
		return -EINVAL;

	if (st)
		csdev->flags |= CLARIION_SHORT_TRESPASS;
	else
		csdev->flags &= ~CLARIION_SHORT_TRESPASS;

	if (hr)
		csdev->flags |= CLARIION_HONOR_RESERVATIONS;
	else
		csdev->flags &= ~CLARIION_HONOR_RESERVATIONS;

	/*
	 * If this path is owned, we have to send a trespass command
	 * with the new parameters. If not, simply return. Next trespass
	 * command would use the parameters.
	 */
	if (csdev->lun_state != CLARIION_LUN_OWNED)
		goto done;

	csdev->lun_state = CLARIION_LUN_UNINITIALIZED;
	result = send_trespass_cmd(sdev, csdev);
	if (result != SCSI_DH_OK)
		goto done;

	/* Update status */
	result = clariion_send_inquiry(sdev, csdev);

done:
	return result;
}