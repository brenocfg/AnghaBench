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
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_window_class ; 
 int /*<<< orphan*/  window_class ; 
 int /*<<< orphan*/  window_class_init_once ; 

__attribute__((used)) static ATOM get_window_class(void)
{
    pthread_once(&window_class_init_once, register_window_class);
    return window_class;
}