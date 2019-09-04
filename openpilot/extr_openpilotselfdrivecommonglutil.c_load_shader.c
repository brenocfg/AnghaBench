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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

GLuint load_shader(GLenum shaderType, const char *src) {
  GLint status = 0, len = 0;
  GLuint shader;

  if (!(shader = glCreateShader(shaderType)))
    return 0;

  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status)
    return shader;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len) {
    char *msg = (char*)malloc(len);
    if (msg) {
      glGetShaderInfoLog(shader, len, NULL, msg);
      msg[len-1] = 0;
      fprintf(stderr, "error compiling shader:\n%s\n", msg);
      free(msg);
    }
  }
  glDeleteShader(shader);
  return 0;
}