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
struct net_device {struct airo_info* ml_priv; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {scalar_t__ event; } ;
struct airo_info {TYPE_1__ power; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int airo_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	int rc = 0;
	struct airo_info *ai = dev->ml_priv;

	if (ai->power.event)
		return 0;

	switch (cmd) {
#ifdef CISCO_EXT
	case AIROIDIFC:
#ifdef AIROOLDIDIFC
	case AIROOLDIDIFC:
#endif
	{
		int val = AIROMAGIC;
		aironet_ioctl com;
		if (copy_from_user(&com,rq->ifr_data,sizeof(com)))
			rc = -EFAULT;
		else if (copy_to_user(com.data,(char *)&val,sizeof(val)))
			rc = -EFAULT;
	}
	break;

	case AIROIOCTL:
#ifdef AIROOLDIOCTL
	case AIROOLDIOCTL:
#endif
		/* Get the command struct and hand it off for evaluation by
		 * the proper subfunction
		 */
	{
		aironet_ioctl com;
		if (copy_from_user(&com,rq->ifr_data,sizeof(com))) {
			rc = -EFAULT;
			break;
		}

		/* Separate R/W functions bracket legality here
		 */
		if ( com.command == AIRORSWVERSION ) {
			if (copy_to_user(com.data, swversion, sizeof(swversion)))
				rc = -EFAULT;
			else
				rc = 0;
		}
		else if ( com.command <= AIRORRID)
			rc = readrids(dev,&com);
		else if ( com.command >= AIROPCAP && com.command <= (AIROPLEAPUSR+2) )
			rc = writerids(dev,&com);
		else if ( com.command >= AIROFLSHRST && com.command <= AIRORESTART )
			rc = flashcard(dev,&com);
		else
			rc = -EINVAL;      /* Bad command in ioctl */
	}
	break;
#endif /* CISCO_EXT */

	// All other calls are currently unsupported
	default:
		rc = -EOPNOTSUPP;
	}
	return rc;
}