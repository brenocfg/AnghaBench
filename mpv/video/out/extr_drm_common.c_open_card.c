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
typedef  int /*<<< orphan*/  card_path ;

/* Variables and functions */
 char* DRM_DEV_NAME ; 
 int /*<<< orphan*/  DRM_DIR_NAME ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int open_card(int card_no)
{
    char card_path[128];
    snprintf(card_path, sizeof(card_path), DRM_DEV_NAME, DRM_DIR_NAME, card_no);
    return open(card_path, O_RDWR | O_CLOEXEC);
}