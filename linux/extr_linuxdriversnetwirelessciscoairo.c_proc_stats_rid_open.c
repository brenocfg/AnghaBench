#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct proc_data {int readlen; int /*<<< orphan*/ * rbuffer; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct inode {int dummy; } ;
struct file {struct proc_data* private_data; } ;
struct airo_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * vals; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ StatsRid ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct net_device* PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  airo_print_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct proc_data*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct proc_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readStatsRid (struct airo_info*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 char** statsLabels ; 
 int strlen (char*) ; 

__attribute__((used)) static int proc_stats_rid_open( struct inode *inode,
				struct file *file,
				u16 rid )
{
	struct proc_data *data;
	struct net_device *dev = PDE_DATA(inode);
	struct airo_info *apriv = dev->ml_priv;
	StatsRid stats;
	int i, j;
	__le32 *vals = stats.vals;
	int len;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	data = file->private_data;
	if ((data->rbuffer = kmalloc( 4096, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}

	readStatsRid(apriv, &stats, rid, 1);
	len = le16_to_cpu(stats.len);

        j = 0;
	for(i=0; statsLabels[i]!=(char *)-1 && i*4<len; i++) {
		if (!statsLabels[i]) continue;
		if (j+strlen(statsLabels[i])+16>4096) {
			airo_print_warn(apriv->dev->name,
			       "Potentially disastrous buffer overflow averted!");
			break;
		}
		j+=sprintf(data->rbuffer+j, "%s: %u\n", statsLabels[i],
				le32_to_cpu(vals[i]));
	}
	if (i*4 >= len) {
		airo_print_warn(apriv->dev->name, "Got a short rid");
	}
	data->readlen = j;
	return 0;
}