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
 int /*<<< orphan*/  mongoc_cleanup () ; 
 int /*<<< orphan*/  mongoc_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mongoc_collection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mongodb_client ; 
 int /*<<< orphan*/  mongodb_collection ; 

void mongodb_cleanup() {
    mongoc_collection_destroy(mongodb_collection);
    mongoc_client_destroy(mongodb_client);
    mongoc_cleanup();

    return;
}