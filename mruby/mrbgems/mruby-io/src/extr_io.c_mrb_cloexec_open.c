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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
#define  EMFILE 129 
#define  ENFILE 128 
 int FALSE ; 
 scalar_t__ O_CLOEXEC ; 
 scalar_t__ O_NOINHERIT ; 
 int /*<<< orphan*/  RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int errno ; 
 int /*<<< orphan*/  mrb_fd_cloexec (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  mrb_garbage_collect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (char const*,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 

int
mrb_cloexec_open(mrb_state *mrb, const char *pathname, mrb_int flags, mrb_int mode)
{
  int fd, retry = FALSE;
  char* fname = mrb_locale_from_utf8(pathname, -1);

#ifdef O_CLOEXEC
  /* O_CLOEXEC is available since Linux 2.6.23.  Linux 2.6.18 silently ignore it. */
  flags |= O_CLOEXEC;
#elif defined O_NOINHERIT
  flags |= O_NOINHERIT;
#endif
reopen:
  fd = open(fname, (int)flags, (fmode_t)mode);
  if (fd == -1) {
    if (!retry) {
      switch (errno) {
        case ENFILE:
        case EMFILE:
        mrb_garbage_collect(mrb);
        retry = TRUE;
        goto reopen;
      }
    }

    mrb_sys_fail(mrb, RSTRING_CSTR(mrb, mrb_format(mrb, "open %s", pathname)));
  }
  mrb_locale_free(fname);

  if (fd <= 2) {
    mrb_fd_cloexec(mrb, fd);
  }
  return fd;
}