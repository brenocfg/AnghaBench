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
struct TYPE_2__ {int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 TYPE_1__ file_loader ; 
 int /*<<< orphan*/  ossl_store_unregister_loader_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void store_file_loader_deinit(void)
{
    ossl_store_unregister_loader_int(file_loader.scheme);
}