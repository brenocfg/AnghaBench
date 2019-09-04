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
struct expansion_card {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct Scsi_Host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fas216_release (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fas216_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 

__attribute__((used)) static void arxescsi_remove(struct expansion_card *ec)
{
	struct Scsi_Host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, NULL);
	fas216_remove(host);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
}