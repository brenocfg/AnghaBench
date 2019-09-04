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
struct hdac_hdmi_priv {int /*<<< orphan*/  num_cvt; int /*<<< orphan*/  cvt_list; } ;
struct hdac_hdmi_cvt {int nid; int /*<<< orphan*/  head; int /*<<< orphan*/  name; } ;
struct hdac_device {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAME_SIZE ; 
 int hdac_hdmi_query_cvt_params (struct hdac_device*,struct hdac_hdmi_cvt*) ; 
 struct hdac_hdmi_priv* hdev_to_hdmi_priv (struct hdac_device*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_cvt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int hdac_hdmi_add_cvt(struct hdac_device *hdev, hda_nid_t nid)
{
	struct hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	struct hdac_hdmi_cvt *cvt;
	char name[NAME_SIZE];

	cvt = kzalloc(sizeof(*cvt), GFP_KERNEL);
	if (!cvt)
		return -ENOMEM;

	cvt->nid = nid;
	sprintf(name, "cvt %d", cvt->nid);
	cvt->name = kstrdup(name, GFP_KERNEL);

	list_add_tail(&cvt->head, &hdmi->cvt_list);
	hdmi->num_cvt++;

	return hdac_hdmi_query_cvt_params(hdev, cvt);
}