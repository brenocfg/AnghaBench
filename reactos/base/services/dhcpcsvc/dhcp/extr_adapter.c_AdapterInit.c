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

/* Variables and functions */
 int /*<<< orphan*/  AdapterList ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSAStartup (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsd ; 

void AdapterInit() {
    WSAStartup(0x0101,&wsd);

    InitializeListHead( &AdapterList );
}