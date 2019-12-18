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
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_zap_mapping (int /*<<< orphan*/ ,struct address_space*) ; 

__attribute__((used)) static void nfs_set_pageerror(struct address_space *mapping)
{
	nfs_zap_mapping(mapping->host, mapping);
}