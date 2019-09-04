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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int16_t ;

/* Variables and functions */
 int EOF ; 
 int FILE_READ_CHUNK ; 
 int LUAL_BUFFERSIZE ; 
 int VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_SEEK_CUR ; 
 char* alloca (int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,char*) ; 
 char* luaM_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_lseek (int,int,int /*<<< orphan*/ ) ; 
 int vfs_read (int,char*,int) ; 

__attribute__((used)) static int file_g_read( lua_State* L, int n, int16_t end_char, int fd )
{
  static char *heap_mem = NULL;
  // free leftover memory
  if (heap_mem) {
    luaM_free(L, heap_mem);
    heap_mem = NULL;
  }

  if(n <= 0)
    n = FILE_READ_CHUNK;

  if(end_char < 0 || end_char >255)
    end_char = EOF;


  if(!fd)
    return luaL_error(L, "open a file first");

  char *p;
  int i;

  if (n > LUAL_BUFFERSIZE) {
    // get buffer from heap
    p = heap_mem = luaM_malloc(L, n);
  } else {
    // small chunks go onto the stack
    p = alloca(n);
  }

  n = vfs_read(fd, p, n);
  // bypass search if no end character provided
  if (n > 0 && end_char != EOF) {
    for (i = 0; i < n; ++i)
      if (p[i] == end_char)
      {
        ++i;
        break;
      }
  } else {
    i = n;
  }

  if (i == 0 || n == VFS_RES_ERR) {
    if (heap_mem) {
      luaM_free(L, heap_mem);
      heap_mem = NULL;
    }
    lua_pushnil(L);
    return 1;
  }

  vfs_lseek(fd, -(n - i), VFS_SEEK_CUR);
  lua_pushlstring(L, p, i);
  if (heap_mem) {
    luaM_free(L, heap_mem);
    heap_mem = NULL;
  }
  return 1;
}