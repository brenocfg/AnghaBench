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
typedef  int /*<<< orphan*/  u64 ;
struct vgic_its {int /*<<< orphan*/  its_lock; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
#define  GITS_CMD_CLEAR 139 
#define  GITS_CMD_DISCARD 138 
#define  GITS_CMD_INT 137 
#define  GITS_CMD_INV 136 
#define  GITS_CMD_INVALL 135 
#define  GITS_CMD_MAPC 134 
#define  GITS_CMD_MAPD 133 
#define  GITS_CMD_MAPI 132 
#define  GITS_CMD_MAPTI 131 
#define  GITS_CMD_MOVALL 130 
#define  GITS_CMD_MOVI 129 
#define  GITS_CMD_SYNC 128 
 int its_cmd_get_command (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_clear (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_discard (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_int (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_inv (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_invall (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_mapc (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_mapd (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_mapi (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_movall (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 
 int vgic_its_cmd_handle_movi (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vgic_its_handle_command(struct kvm *kvm, struct vgic_its *its,
				   u64 *its_cmd)
{
	int ret = -ENODEV;

	mutex_lock(&its->its_lock);
	switch (its_cmd_get_command(its_cmd)) {
	case GITS_CMD_MAPD:
		ret = vgic_its_cmd_handle_mapd(kvm, its, its_cmd);
		break;
	case GITS_CMD_MAPC:
		ret = vgic_its_cmd_handle_mapc(kvm, its, its_cmd);
		break;
	case GITS_CMD_MAPI:
		ret = vgic_its_cmd_handle_mapi(kvm, its, its_cmd);
		break;
	case GITS_CMD_MAPTI:
		ret = vgic_its_cmd_handle_mapi(kvm, its, its_cmd);
		break;
	case GITS_CMD_MOVI:
		ret = vgic_its_cmd_handle_movi(kvm, its, its_cmd);
		break;
	case GITS_CMD_DISCARD:
		ret = vgic_its_cmd_handle_discard(kvm, its, its_cmd);
		break;
	case GITS_CMD_CLEAR:
		ret = vgic_its_cmd_handle_clear(kvm, its, its_cmd);
		break;
	case GITS_CMD_MOVALL:
		ret = vgic_its_cmd_handle_movall(kvm, its, its_cmd);
		break;
	case GITS_CMD_INT:
		ret = vgic_its_cmd_handle_int(kvm, its, its_cmd);
		break;
	case GITS_CMD_INV:
		ret = vgic_its_cmd_handle_inv(kvm, its, its_cmd);
		break;
	case GITS_CMD_INVALL:
		ret = vgic_its_cmd_handle_invall(kvm, its, its_cmd);
		break;
	case GITS_CMD_SYNC:
		/* we ignore this command: we are in sync all of the time */
		ret = 0;
		break;
	}
	mutex_unlock(&its->its_lock);

	return ret;
}