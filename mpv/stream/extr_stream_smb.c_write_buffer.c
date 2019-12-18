#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_lock ; 
 int smbc_write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int write_buffer(stream_t *s, void *buffer, int len) {
  struct priv *p = s->priv;
  int wr;
  pthread_mutex_lock(&smb_lock);
  wr = smbc_write(p->fd,buffer,len);
  pthread_mutex_unlock(&smb_lock);
  return wr;
}