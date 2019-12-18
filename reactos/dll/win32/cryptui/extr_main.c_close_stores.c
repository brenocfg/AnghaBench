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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCM_GETITEMCOUNT ; 
 int /*<<< orphan*/  cert_mgr_index_to_store (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void close_stores(HWND tab)
{
    int i, tabs = SendMessageW(tab, TCM_GETITEMCOUNT, 0, 0);

    for (i = 0; i < tabs; i++)
        CertCloseStore(cert_mgr_index_to_store(tab, i), 0);
}