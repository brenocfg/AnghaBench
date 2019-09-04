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
struct iss_ipipe_device {int dummy; } ;
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCK_MMR ; 
 int /*<<< orphan*/  IPIPE_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRC_COL ; 
 int /*<<< orphan*/  SRC_EN ; 
 int /*<<< orphan*/  SRC_FMT ; 
 int /*<<< orphan*/  SRC_HPS ; 
 int /*<<< orphan*/  SRC_HSZ ; 
 int /*<<< orphan*/  SRC_MODE ; 
 int /*<<< orphan*/  SRC_VPS ; 
 int /*<<< orphan*/  SRC_VSZ ; 
 int /*<<< orphan*/  YUV_PHS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct iss_device* to_iss_device (struct iss_ipipe_device*) ; 

__attribute__((used)) static void ipipe_print_status(struct iss_ipipe_device *ipipe)
{
	struct iss_device *iss = to_iss_device(ipipe);

	dev_dbg(iss->dev, "-------------IPIPE Register dump-------------\n");

	IPIPE_PRINT_REGISTER(iss, SRC_EN);
	IPIPE_PRINT_REGISTER(iss, SRC_MODE);
	IPIPE_PRINT_REGISTER(iss, SRC_FMT);
	IPIPE_PRINT_REGISTER(iss, SRC_COL);
	IPIPE_PRINT_REGISTER(iss, SRC_VPS);
	IPIPE_PRINT_REGISTER(iss, SRC_VSZ);
	IPIPE_PRINT_REGISTER(iss, SRC_HPS);
	IPIPE_PRINT_REGISTER(iss, SRC_HSZ);
	IPIPE_PRINT_REGISTER(iss, GCK_MMR);
	IPIPE_PRINT_REGISTER(iss, YUV_PHS);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
}