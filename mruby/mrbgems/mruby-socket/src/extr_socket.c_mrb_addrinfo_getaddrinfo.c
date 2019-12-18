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
struct addrinfo {int ai_flags; int ai_family; int ai_socktype; int ai_protocol; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  E_SOCKET_ERROR ; 
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 char* RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_cptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_cptr_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_cptr_value (int /*<<< orphan*/ *,struct addrinfo*) ; 
 int /*<<< orphan*/  mrb_cv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_cv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_addrinfo_getaddrinfo(mrb_state *mrb, mrb_value klass)
{
  struct addrinfo hints, *res0, *res;
  mrb_value ai, ary, family, lastai, nodename, protocol, sa, service, socktype;
  mrb_int flags;
  int arena_idx, error;
  const char *hostname = NULL, *servname = NULL;

  ary = mrb_ary_new(mrb);
  arena_idx = mrb_gc_arena_save(mrb);  /* ary must be on arena! */

  family = socktype = protocol = mrb_nil_value();
  flags = 0;
  mrb_get_args(mrb, "oo|oooi", &nodename, &service, &family, &socktype, &protocol, &flags);

  if (mrb_string_p(nodename)) {
    hostname = RSTRING_CSTR(mrb, nodename);
  } else if (mrb_nil_p(nodename)) {
    hostname = NULL;
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "nodename must be String or nil");
  }

  if (mrb_string_p(service)) {
    servname = RSTRING_CSTR(mrb, service);
  } else if (mrb_fixnum_p(service)) {
    servname = RSTRING_PTR(mrb_fixnum_to_str(mrb, service, 10));
  } else if (mrb_nil_p(service)) {
    servname = NULL;
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "service must be String, Fixnum, or nil");
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = (int)flags;

  if (mrb_fixnum_p(family)) {
    hints.ai_family = (int)mrb_fixnum(family);
  }

  if (mrb_fixnum_p(socktype)) {
    hints.ai_socktype = (int)mrb_fixnum(socktype);
  }

  if (mrb_fixnum_p(protocol)) {
    hints.ai_protocol = (int)mrb_fixnum(protocol);
  }

  lastai = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "_lastai"));
  if (mrb_cptr_p(lastai)) {
    freeaddrinfo((struct addrinfo*)mrb_cptr(lastai));
    mrb_cv_set(mrb, klass, mrb_intern_lit(mrb, "_lastai"), mrb_nil_value());
  }

  error = getaddrinfo(hostname, servname, &hints, &res0);
  if (error) {
    mrb_raisef(mrb, E_SOCKET_ERROR, "getaddrinfo: %s", gai_strerror(error));
  }
  mrb_cv_set(mrb, klass, mrb_intern_lit(mrb, "_lastai"), mrb_cptr_value(mrb, res0));

  for (res = res0; res != NULL; res = res->ai_next) {
    sa = mrb_str_new(mrb, (char*)res->ai_addr, res->ai_addrlen);
    ai = mrb_funcall(mrb, klass, "new", 4, sa, mrb_fixnum_value(res->ai_family), mrb_fixnum_value(res->ai_socktype), mrb_fixnum_value(res->ai_protocol));
    mrb_ary_push(mrb, ary, ai);
    mrb_gc_arena_restore(mrb, arena_idx);
  }

  freeaddrinfo(res0);
  mrb_cv_set(mrb, klass, mrb_intern_lit(mrb, "_lastai"), mrb_nil_value());

  return ary;
}