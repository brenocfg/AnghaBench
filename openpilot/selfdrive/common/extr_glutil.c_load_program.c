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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_shader (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

GLuint load_program(const char *vert_src, const char *frag_src) {
  GLuint vert, frag, prog;
  GLint status = 0, len = 0;

  if (!(vert = load_shader(GL_VERTEX_SHADER, vert_src)))
    return 0;
  if (!(frag = load_shader(GL_FRAGMENT_SHADER, frag_src)))
    goto fail_frag;
  if (!(prog = glCreateProgram()))
    goto fail_prog;

  glAttachShader(prog, vert);
  glAttachShader(prog, frag);
  glLinkProgram(prog);

  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (status)
    return prog;

  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
  if (len) {
    char *buf = (char*) malloc(len);
    if (buf) {
      glGetProgramInfoLog(prog, len, NULL, buf);
      buf[len-1] = 0;
      fprintf(stderr, "error linking program:\n%s\n", buf);
      free(buf);
    }
  }
  glDeleteProgram(prog);
fail_prog:
  glDeleteShader(frag);
fail_frag:
  glDeleteShader(vert);
  return 0;
}