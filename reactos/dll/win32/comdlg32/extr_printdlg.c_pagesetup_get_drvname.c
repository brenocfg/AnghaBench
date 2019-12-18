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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  devnames_driver_name ; 
 int /*<<< orphan*/ * pagesetup_get_a_devname (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *pagesetup_get_drvname(const pagesetup_data *data)
{
    return pagesetup_get_a_devname(data, devnames_driver_name);
}