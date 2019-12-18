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
typedef  int /*<<< orphan*/  uint8_t ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ buf_printf (struct buffer*,char*,char const*) ; 
 int /*<<< orphan*/  buf_set_write (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,int /*<<< orphan*/ ,char const*) ; 

void
setenv_str_safe(struct env_set *es, const char *name, const char *value)
{
    uint8_t b[64];
    struct buffer buf;
    buf_set_write(&buf, b, sizeof(b));
    if (buf_printf(&buf, "OPENVPN_%s", name))
    {
        setenv_str(es, BSTR(&buf), value);
    }
    else
    {
        msg(M_WARN, "setenv_str_safe: name overflow");
    }
}