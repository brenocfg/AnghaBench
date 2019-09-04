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
struct usb_string {int /*<<< orphan*/  id; } ;
struct usb_gadget_strings {struct usb_string* strings; } ;
struct usb_gadget_string_container {int /*<<< orphan*/  list; } ;
struct usb_composite_dev {int /*<<< orphan*/  gstrings; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usb_string* ERR_CAST (struct usb_gadget_string_container*) ; 
 struct usb_string* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct usb_gadget_string_container*) ; 
 struct usb_gadget_string_container* copy_gadget_strings (struct usb_gadget_strings**,unsigned int,unsigned int) ; 
 struct usb_gadget_strings** get_containers_gs (struct usb_gadget_string_container*) ; 
 int /*<<< orphan*/  kfree (struct usb_gadget_string_container*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usb_string_ids_tab (struct usb_composite_dev*,struct usb_string*) ; 

struct usb_string *usb_gstrings_attach(struct usb_composite_dev *cdev,
		struct usb_gadget_strings **sp, unsigned n_strings)
{
	struct usb_gadget_string_container *uc;
	struct usb_gadget_strings **n_gs;
	unsigned n_gstrings = 0;
	unsigned i;
	int ret;

	for (i = 0; sp[i]; i++)
		n_gstrings++;

	if (!n_gstrings)
		return ERR_PTR(-EINVAL);

	uc = copy_gadget_strings(sp, n_gstrings, n_strings);
	if (IS_ERR(uc))
		return ERR_CAST(uc);

	n_gs = get_containers_gs(uc);
	ret = usb_string_ids_tab(cdev, n_gs[0]->strings);
	if (ret)
		goto err;

	for (i = 1; i < n_gstrings; i++) {
		struct usb_string *m_s;
		struct usb_string *s;
		unsigned n;

		m_s = n_gs[0]->strings;
		s = n_gs[i]->strings;
		for (n = 0; n < n_strings; n++) {
			s->id = m_s->id;
			s++;
			m_s++;
		}
	}
	list_add_tail(&uc->list, &cdev->gstrings);
	return n_gs[0]->strings;
err:
	kfree(uc);
	return ERR_PTR(ret);
}