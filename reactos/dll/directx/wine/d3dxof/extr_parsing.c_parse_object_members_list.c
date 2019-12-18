#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {size_t nb_members; TYPE_4__* members; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ xtemplate ;
struct TYPE_19__ {size_t level; scalar_t__ cur_pstrings; scalar_t__ pstrings; TYPE_3__* pxo; scalar_t__ cur_pos_data; scalar_t__ pdata; scalar_t__ value; TYPE_5__* pdxf; TYPE_6__** pxt; } ;
typedef  TYPE_7__ parse_buffer ;
typedef  size_t WORD ;
typedef  size_t ULONG ;
struct TYPE_17__ {size_t nb_xtemplates; TYPE_6__* xtemplates; } ;
struct TYPE_16__ {size_t nb_dims; size_t* dim_value; scalar_t__ type; size_t idx_template; int /*<<< orphan*/  name; scalar_t__* dim_fixed; } ;
struct TYPE_15__ {size_t nb_members; TYPE_2__* members; TYPE_1__* root; } ;
struct TYPE_14__ {scalar_t__ start; scalar_t__ size; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {scalar_t__ pdata; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  char* LPCSTR ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,...) ; 
 scalar_t__ MAX_STRINGS_BUFFER ; 
 size_t TOKEN_COMMA ; 
 scalar_t__ TOKEN_DWORD ; 
 size_t TOKEN_FLOAT ; 
 size_t TOKEN_INTEGER ; 
 size_t TOKEN_LPSTR ; 
 scalar_t__ TOKEN_NAME ; 
 size_t TOKEN_SEMICOLON ; 
 scalar_t__ TOKEN_WORD ; 
 int /*<<< orphan*/  TRACE (char*,size_t,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,size_t) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t check_TOKEN (TYPE_7__*) ; 
 int /*<<< orphan*/  check_buffer (TYPE_7__*,int) ; 
 int /*<<< orphan*/  get_TOKEN (TYPE_7__*) ; 
 int /*<<< orphan*/  parse_object_parts (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL parse_object_members_list(parse_buffer * buf)
{
  DWORD token;
  ULONG i;
  xtemplate* pt = buf->pxt[buf->level];

  buf->pxo->nb_members = pt->nb_members;

  for (i = 0; i < pt->nb_members; i++)
  {
    ULONG k;
    ULONG nb_elems = 1;
    BOOL basic_type = TRUE;

    buf->pxo->members[i].name = pt->members[i].name;
    buf->pxo->members[i].start = buf->cur_pos_data;

    for (k = 0; k < pt->members[i].nb_dims; k++)
    {
      if (pt->members[i].dim_fixed[k])
        nb_elems *= pt->members[i].dim_value[k];
      else
        nb_elems *= *(DWORD*)(buf->pxo->root->pdata + buf->pxo->members[pt->members[i].dim_value[k]].start);
    }

    TRACE("Elements to consider: %u\n", nb_elems);

    for (k = 0; k < nb_elems; k++)
    {
      if (pt->members[i].type == TOKEN_NAME)
      {
        ULONG j;

        TRACE("Found sub-object %s\n", buf->pdxf->xtemplates[pt->members[i].idx_template].name);
        basic_type = FALSE;
        buf->level++;
        /* To do template lookup */
        for (j = 0; j < buf->pdxf->nb_xtemplates; j++)
        {
          if (!_strnicmp(buf->pdxf->xtemplates[pt->members[i].idx_template].name, buf->pdxf->xtemplates[j].name, -1))
          {
            buf->pxt[buf->level] = &buf->pdxf->xtemplates[j];
            break;
          }
        }
        if (j == buf->pdxf->nb_xtemplates)
        {
          ERR("Unknown template %s\n", (char*)buf->value);
          buf->level--;
          return FALSE;
        }
        TRACE("Enter %s\n", buf->pdxf->xtemplates[pt->members[i].idx_template].name);
        if (!parse_object_parts(buf, FALSE))
        {
          buf->level--;
          return FALSE;
        }
        buf->level--;
      }
      else
      {
        token = check_TOKEN(buf);
        if (token == TOKEN_INTEGER)
        {
          get_TOKEN(buf);
          TRACE("%s = %d\n", pt->members[i].name, *(DWORD*)buf->value);
          /* Assume larger size */
          if (!check_buffer(buf, 4))
            return FALSE;
          if (pt->members[i].type == TOKEN_WORD)
          {
              *(WORD *)(buf->pdata + buf->cur_pos_data) = *(DWORD *)buf->value;
              buf->cur_pos_data += 2;
          }
          else if (pt->members[i].type == TOKEN_DWORD)
          {
              *(DWORD *)(buf->pdata + buf->cur_pos_data) = *(DWORD *)buf->value;
              buf->cur_pos_data += 4;
          }
          else
          {
            FIXME("Token %d not supported\n", pt->members[i].type);
            return FALSE;
          }
        }
        else if (token == TOKEN_FLOAT)
        {
          get_TOKEN(buf);
          TRACE("%s = %f\n", pt->members[i].name, *(float*)buf->value);
          if (!check_buffer(buf, 4))
            return FALSE;
          if (pt->members[i].type == TOKEN_FLOAT)
          {
              *(float *)(buf->pdata + buf->cur_pos_data) = *(float *)buf->value;
              buf->cur_pos_data += 4;
          }
          else
          {
            FIXME("Token %d not supported\n", pt->members[i].type);
            return FALSE;
          }
        }
        else if (token == TOKEN_LPSTR)
        {
          get_TOKEN(buf);
          TRACE("%s = %s\n", pt->members[i].name, (char*)buf->value);
          if (!check_buffer(buf, sizeof(LPSTR)))
            return FALSE;
          if (pt->members[i].type == TOKEN_LPSTR)
          {
            int len = strlen((char*)buf->value) + 1;
            if ((buf->cur_pstrings - buf->pstrings + len) > MAX_STRINGS_BUFFER)
            {
              FIXME("Buffer too small %p %p %d\n", buf->cur_pstrings, buf->pstrings, len);
              return FALSE;
            }
            strcpy((char*)buf->cur_pstrings, (char*)buf->value);
            *(((LPCSTR*)(buf->pdata + buf->cur_pos_data))) = (char*)buf->cur_pstrings;
            buf->cur_pstrings += len;
            buf->cur_pos_data += sizeof(LPSTR);
          }
          else
          {
            FIXME("Token %d not supported\n", pt->members[i].type);
            return FALSE;
          }
        }
        else
        {
          WARN("Unexpected token %d\n", token);
          return FALSE;
        }
      }

      if (basic_type)
      {
        /* Handle separator only for basic types */
        token = check_TOKEN(buf);
        if ((token != TOKEN_COMMA) && (token != TOKEN_SEMICOLON))
          return FALSE;
        /* Allow multi-semicolons + single comma separator */
        while (check_TOKEN(buf) == TOKEN_SEMICOLON)
          get_TOKEN(buf);
        if (check_TOKEN(buf) == TOKEN_COMMA)
          get_TOKEN(buf);
      }
    }

    buf->pxo->members[i].size = buf->cur_pos_data - buf->pxo->members[i].start;
  }

  return TRUE;
}