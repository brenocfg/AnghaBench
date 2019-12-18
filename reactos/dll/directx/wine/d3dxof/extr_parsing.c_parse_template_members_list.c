#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pdxf; scalar_t__ value; } ;
typedef  TYPE_3__ parse_buffer ;
struct TYPE_11__ {scalar_t__ type; int idx_template; char* name; int* dim_value; int nb_dims; void** dim_fixed; } ;
typedef  TYPE_4__ member ;
struct TYPE_9__ {size_t nb_xtemplates; TYPE_1__* xtemplates; } ;
struct TYPE_8__ {int nb_members; TYPE_4__* members; int /*<<< orphan*/  name; } ;
typedef  int DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int MAX_ARRAY_DIM ; 
 scalar_t__ TOKEN_ARRAY ; 
 scalar_t__ TOKEN_CBRACKET ; 
 scalar_t__ TOKEN_DWORD ; 
 scalar_t__ TOKEN_INTEGER ; 
 scalar_t__ TOKEN_NAME ; 
 scalar_t__ TOKEN_OBRACKET ; 
 scalar_t__ TOKEN_SEMICOLON ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*,char*) ; 
 int /*<<< orphan*/  _strnicmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_TOKEN (TYPE_3__*) ; 
 scalar_t__ get_TOKEN (TYPE_3__*) ; 
 scalar_t__ is_primitive_type (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static BOOL parse_template_members_list(parse_buffer * buf)
{
  int idx_member = 0;
  member* cur_member;

  while (1)
  {
    BOOL array = FALSE;
    int nb_dims = 0;
    cur_member = &buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates].members[idx_member];

    if (check_TOKEN(buf) == TOKEN_ARRAY)
    {
      get_TOKEN(buf);
      array = TRUE;
    }

    if (check_TOKEN(buf) == TOKEN_NAME)
    {
      cur_member->type = get_TOKEN(buf);
      if (!strcmp((char*)buf->value, "indexColor"))
      {
        /* Case sensitive legacy type indexColor is described in the first template */
        cur_member->idx_template = 0;
      }
      else
      {
        cur_member->idx_template = 1;
        while (cur_member->idx_template < buf->pdxf->nb_xtemplates)
        {
          if (!_strnicmp((char*)buf->value, buf->pdxf->xtemplates[cur_member->idx_template].name, -1))
            break;
          cur_member->idx_template++;
        }
        if (cur_member->idx_template == buf->pdxf->nb_xtemplates)
        {
          WARN("Reference to a nonexistent template '%s'\n", (char*)buf->value);
          return FALSE;
        }
      }
    }
    else if (is_primitive_type(check_TOKEN(buf)))
      cur_member->type = get_TOKEN(buf);
    else
      break;

    if (get_TOKEN(buf) != TOKEN_NAME)
      return FALSE;
    strcpy(cur_member->name, (char*)buf->value);

    if (array)
    {
      while (check_TOKEN(buf) == TOKEN_OBRACKET)
      {
        if (nb_dims >= MAX_ARRAY_DIM)
        {
          FIXME("Too many dimensions (%d) for multi-dimensional array\n", nb_dims + 1);
          return FALSE;
        }
        get_TOKEN(buf);
        if (check_TOKEN(buf) == TOKEN_INTEGER)
        {
          get_TOKEN(buf);
          cur_member->dim_fixed[nb_dims] = TRUE;
          cur_member->dim_value[nb_dims] = *(DWORD*)buf->value;
        }
        else
        {
          int i;
          if (get_TOKEN(buf) != TOKEN_NAME)
            return FALSE;
          for (i = 0; i < idx_member; i++)
          {
            if (!strcmp((char*)buf->value, buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates].members[i].name))
            {
              if (buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates].members[i].nb_dims)
              {
                ERR("Array cannot be used to specify variable array size\n");
                return FALSE;
              }
              if (buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates].members[i].type != TOKEN_DWORD)
              {
                FIXME("Only DWORD supported to specify variable array size\n");
                return FALSE;
              }
              break;
            }
          }
          if (i == idx_member)
          {
            ERR("Reference to unknown member %s\n", (char*)buf->value);
            return FALSE;
          }
          cur_member->dim_fixed[nb_dims] = FALSE;
          cur_member->dim_value[nb_dims] = i;
        }
        if (get_TOKEN(buf) != TOKEN_CBRACKET)
          return FALSE;
        nb_dims++;
      }
      if (!nb_dims)
        return FALSE;
      cur_member->nb_dims = nb_dims;
    }
    if (get_TOKEN(buf) != TOKEN_SEMICOLON)
      return FALSE;

    idx_member++;
  }

  buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates].nb_members = idx_member;

  return TRUE;
}