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
struct RString {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMBED ; 
 char* RSTR_EMBED_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_EMBED_LEN (struct RString*,size_t) ; 
 int /*<<< orphan*/  RSTR_SET_TYPE_FLAG (struct RString*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static struct RString*
str_init_embed(struct RString *s, const char *p, size_t len)
{
  if (p) memcpy(RSTR_EMBED_PTR(s), p, len);
  RSTR_EMBED_PTR(s)[len] = '\0';
  RSTR_SET_TYPE_FLAG(s, EMBED);
  RSTR_SET_EMBED_LEN(s, len);
  return s;
}