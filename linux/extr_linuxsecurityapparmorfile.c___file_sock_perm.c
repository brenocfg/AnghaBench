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
typedef  scalar_t__ u32 ;
struct socket {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 scalar_t__ aa_label_is_subset (struct aa_label*,struct aa_label*) ; 
 int aa_sock_file_perm (struct aa_label*,char const*,scalar_t__,struct socket*) ; 
 int /*<<< orphan*/  file_ctx (struct file*) ; 
 int /*<<< orphan*/  last_error (int,int) ; 
 int /*<<< orphan*/  update_file_ctx (int /*<<< orphan*/ ,struct aa_label*,scalar_t__) ; 

__attribute__((used)) static int __file_sock_perm(const char *op, struct aa_label *label,
			    struct aa_label *flabel, struct file *file,
			    u32 request, u32 denied)
{
	struct socket *sock = (struct socket *) file->private_data;
	int error;

	AA_BUG(!sock);

	/* revalidation due to label out of date. No revocation at this time */
	if (!denied && aa_label_is_subset(flabel, label))
		return 0;

	/* TODO: improve to skip profiles cached in flabel */
	error = aa_sock_file_perm(label, op, request, sock);
	if (denied) {
		/* TODO: improve to skip profiles checked above */
		/* check every profile in file label to is cached */
		last_error(error, aa_sock_file_perm(flabel, op, request, sock));
	}
	if (!error)
		update_file_ctx(file_ctx(file), label, request);

	return error;
}