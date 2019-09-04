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
struct TYPE_3__ {int /*<<< orphan*/  pos; struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_lock ; 
 int /*<<< orphan*/  smbc_lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control(stream_t *s, int cmd, void *arg) {
  struct priv *p = s->priv;
  switch(cmd) {
    case STREAM_CTRL_GET_SIZE: {
      pthread_mutex_lock(&smb_lock);
      off_t size = smbc_lseek(p->fd,0,SEEK_END);
      smbc_lseek(p->fd,s->pos,SEEK_SET);
      pthread_mutex_unlock(&smb_lock);
      if(size != (off_t)-1) {
        *(int64_t *)arg = size;
        return 1;
      }
    }
    break;
  }
  return STREAM_UNSUPPORTED;
}